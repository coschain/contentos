# Introducing Contentos

Contentos Website: https://www.contentos.io

Contentos White Paper: https://www.contentos.io/subject/home/pdfs/white_paper_en.pdf


Follow us on https://twitter.com/contentosio

Join discussion at https://t.me/ContentoOfficialGroup

# Building

## Building on macOS X

### Install Xcode and Homebrew

Install Xcode and its command line tools by following the instructions here: https://guide.macports.org/#installing.xcode.
In OS X 10.11 (El Capitan) and newer, you will be prompted to install developer tools when running a developer command in the terminal.

Accept the Xcode license if you have not already:

    sudo xcodebuild -license accept

Install Homebrew by following the instructions here: http://brew.sh/

### Initialize Homebrew:

    brew doctor
    brew update

### Install Contentos dependencies:

    brew install \
        autoconf \
        automake \
        cmake \
        git \
        boost \
        libtool \
        openssl \
        python3 \
        
    pip3 install --user jinja2

*Optional.* To use TCMalloc in LevelDB:

    brew install google-perftools

*Optional.* To use cli_wallet and override macOS's default readline installation:

    brew install --force readline
    brew link --force readline

### Install LLVM with WASM support

    ./install_llvm_darwin.sh

Contentos uses WASM as the underlying platform for smart contracts. Contract codes compiling requires LLVM with WASM support. `install_llvm_darwin.sh` will download, build and install LLVM WASM compiler in one go.

### Clone the Repository

    git clone --recurse-submodules https://github.com/coschain/contentos.git
    cd contentos

### Compile

    export OPENSSL_ROOT_DIR=/usr/local/opt/openssl
    export BOOST_ROOT=$(brew --prefix)/Cellar/boost@1.67/1.67.0/
    mkdir build && cd build
    cmake -DBOOST_ROOT="$BOOST_ROOT" -DCMAKE_BUILD_TYPE=Release -DBUILD_CONTENTOS_TESTNET=ON ..
    make -j$(sysctl -n hw.logicalcpu)

Above commands use `-DBUILD_CONTENTOS_TESTNET=ON` for a private testnet. You need to remove this option for public Contentos network.

Also, some useful build targets for `make` are:

    contentosd
    chain_test
    cli_wallet

e.g.:

    make -j$(sysctl -n hw.logicalcpu) contentosd

This will only build `contentosd`.

## Building on Ubuntu

coming soon.

## Building under Docker

coming soon.

# Private testnet

Once `contentosd` and `cli_wallet` were successfully built, you can try performing some basic operations to the chain in private net.

## contentosd

    cd build/programs/contentosd
    ./contentosd

 `contentosd` will output something like the following when it's launched for the first time, 

    ------------------------------------------------------
    
                STARTING TEST NETWORK
    
    ------------------------------------------------------
    initminer public key: COS6QHBEC2FEGqvNyaw5tupW6v2ojcHZR1k4EtNpZu5bssygjnpnV
    initminer private key: 5HvTVEQCYAhVTCV347DEb3tgsCV7o4Xg6wwcJ6zqBdNRU6TEueN
    chain id: 0000000000000000000000000000000000000000000000000000000000000000
    blockchain version: 0.0.1
    ------------------------------------------------------
    th_a  main.cpp:141             main           ] Writing new config file at ...
    th_a  witness_plugin.cpp:507   plugin_startup ] No witnesses configured! ...

It gives the public and private key of `initminer`, which is the very first and built-in account of Contentos network. And it  complains about witness configuration. We will solve the configuration problem in the next step.

## config.ini

`contentosd` creates a fresh new `config.ini` in the `./witness_node_data_dir/` directory by default.

`config.ini` is important because it controls  `contentosd`'s behaviors . Different `config.ini` contents result in different types of nodes in Contentos network. For witness node in a private net, make changes below, or you can simply replace it with content of [example_config_private_net.ini](./example_config_private_net.ini).

    ...
    # p2p-endpoint =
    p2p-endpoint = 127.0.0.1:8888
    ...
    # rpc-endpoint =
    rpc-endpoint = 127.0.0.1:8090
    ...
    # enable-stale-production =
    enable-stale-production = true
    ...
    # required-participation =
    required-participation = 0
    ...
    # witness = 
    witness = "initminer"
    ...
    # private-key =
    private-key = 5HvTVEQCYAhVTCV347DEb3tgsCV7o4Xg6wwcJ6zqBdNRU6TEueN
    ...
    [logger.default]
    level=debug
    ...
    [logger.p2p]
    level=debug
    ...

Run `contentosd` again, and you will see welcome message and block producing information, which means the block chain has been successfully launched.

    ********************************
    *                              *
    *   ------- NEW CHAIN ------   *
    *   - Welcome to Contento! -   *
    *   ------------------------   *
    *                              *
    ********************************
    
    ...
    th_a  witness_plugin.cpp:568  block_production_loo ] Generated block #1 ... by initminer
    th_a  witness_plugin.cpp:568  block_production_loo ] Generated block #2 ... by initminer
    th_a  witness_plugin.cpp:568  block_production_loo ] Generated block #3 ... by initminer
    ...

`contentosd` set up a websocket RPC server on localhost::8090, which was specified by the `rpc-endpoint` line in `config.ini`. So that RPC clients can communicate with `contentosd` node.

Alternatively, you can specify the server address through command line,

    ./contentosd --rpc-endpoint=<host>:<port>

If an HTTP-based RPC server is preferred, modify the `rpc-http-endpoint` line in `config.ini`, or

    ./contentosd --rpc-http-endpoint=<host>:<port>

For detailed command line options, run `./contentosd --help`.

## cli_wallet

`cli_wallet` is a utility to manage your account keys and also an RPC client for sending requests to remote  `contentosd` node.

    cd build/programs/cli_wallet
    ./cli_wallet
    Please use the set_password method to initialize a new wallet before continuing
    new >>> set_password 123
    locked >>> unlock 123
    unlocked >>>

`cli_wallet` will connect to the default RPC server of localhost:8090. Once connected, it provides an interactive console and waits for commands. In the above session, we created a new wallet using `set_password` and set wallet password as "123", then unlocked the wallet using its password.

`cli_wallet --server-endpoint=ws://<host>:<port> ` can be used to connect an RPC server other than the default one. You can find all command line options by running  `cli_wallet --help`. 

### Import private key of initminer

    unlocked >>> import_key 5HvTVEQCYAhVTCV347DEb3tgsCV7o4Xg6wwcJ6zqBdNRU6TEueN
    import_key 5HvTVEQCYAhVTCV347DEb3tgsCV7o4Xg6wwcJ6zqBdNRU6TEueN
    unlocked >>> list_keys
    list_keys
    [[
    "COS6QHBEC2FEGqvNyaw5tupW6v2ojcHZR1k4EtNpZu5bssygjnpnV",
    "5HvTVEQCYAhVTCV347DEb3tgsCV7o4Xg6wwcJ6zqBdNRU6TEueN"
     ]
    ]
    unlocked >>>

By importing private key of `initminer`, we can now perform operations on behalf of `initminer`.

### Create accounts

To create accounts `alice` and `bob` , 

    unlocked >>> create_account initminer alice "" true
    ...
    unlocked >>> create_account initminer bob "" true
    ...
    unlocked >>> list_my_accounts
    alice     0.000 COS       0.030 VESTS
    bob       0.000 COS       0.030 VESTS
    -------------------------------------------------
    TOTAL     0.000 COS       0.060 VESTS
    
    unlocked >>> get_account alice
    {
      "id": 4,
      "name": "alice",
      ...
    }

### Transfer COS

In a private net, `initminer` holds the initial supply of COS's. To transfer COS's between accounts,

    unlocked >>> transfer initminer alice "1000.000 COS" "" true
    unlocked >>> transfer alice bob "300.000 COS" "" true
    unlocked >>> list_my_accounts
    alice     700.000 COS       0.030 VESTS
    bob       300.000 COS       0.030 VESTS
    -------------------------------------------------
    TOTAL    1000.000 COS       0.060 VESTS

### Post an article

To post an article and/or a comment,

    unlocked >>> post_subject alice post1 pet "cats" "blablabla.." "{\"tags\":[\"cat\"]}" true
    unlocked >>> post_comment bob comment1 alice post1 "cool!" "" true

### Other operations

cli_wallet supports a rich set of commands. You can run help in the console to get the full list.

    unlocked >>> help

