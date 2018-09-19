#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>
#include <fc/compress/zlib.hpp>
#include <fc/exception/exception.hpp>

struct Article {
    std::istringstream input{R"(# Introducing Contentos (beta)

Contentos is a Delegated Proof of Stake blockchain that uses a "Proof of Brain" social consnensus algorithm for token allocation.

  - Currency symbol COS.
  - 10% APR inflation narrowing to 1% APR over 20 years.
  - 75% of inflation to "Proof of Brain" social consensus algorithm.
  - 15% of inflation to stake holders.
  - 10% of inflation to block producers.

# No Support & No Warranty

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

# Whitepaper

You can read the Contentos Whitepaper at [https://www.contentos.io/subject/home/generic/web/viewer.html?file=wp1_en.pdf).

# Quickstart

Just want to get up and running quickly? We have pre-build docker images for your convenience. More details are in our [quickstart guide](https://github.com/coschain/contentos/blob/master/doc/exchangequickstart.md).

# Building

We strongly recommend using one of our pre-built Docker images or using Docker to build Contentos. Both of these processes are described in the [quickstart guide](https://github.com/coschain/contentos/blob/master/doc/exchangequickstart.md).

If you would still like to build from source, we do have [build instructions](https://github.com/coschain/contentos/blob/master/doc/building.md) for Linux (Ubuntu LTS) and macOS X.

## Dockerized p2p Node

To run a p2p node (ca. 2GB of memory is required at the moment):

    docker run \
        -d -p 2001:2001 -p 8090:8090 --name contentosd-default \
        contentos/contentos

    docker logs -f contentosd-default  # follow along

## Dockerized Full Node

To run a node with *all* the data (e.g. for supporting a content website)
that uses ca. 14GB of memory and growing:

    docker run \
        --env USE_WAY_TOO_MUCH_RAM=1 --env USE_FULL_WEB_NODE=1 \
        -d -p 2001:2001 -p 8090:8090 --name contentosd-full \
        contentos/contentos

    docker logs -f contentosd-full

# Environment variables

There are quite a few environment variables that can be set to run contentosd in different ways:

* `USE_WAY_TOO_MUCH_RAM` - if set to true, contentosd starts a 'full node'
* `USE_FULL_WEB_NODE` - if set to true, a default config file will be used that enables a full set of API's and associated plugins.
* `USE_NGINX_FRONTEND` - if set to true, this will enable an NGINX reverse proxy in front of contentosd that proxies websocket requests to contentosd. This will also enable a custom healtcheck at the path '/health' that lists how many seconds away from current blockchain time your node is. It will return a '200' if it's less than 60 seconds away from synced.
* `USE_MULTICORE_READONLY` - if set to true, this will enable contentosd in multiple reader mode to take advantage of multiple cores (if available). Read requests are handled by the read-only nodes, and write requests are forwarded back to the single 'writer' node automatically. NGINX load balances all requests to the reader nodes, 4 per available core. This setting is still considered experimental and may have trouble with some API calls until further development is completed.
* `HOME` - set this to the path where you want contentosd to store it's data files (block log, shared memory, config file, etc). By default `/var/lib/contentosd` is used and exists inside the docker container. If you want to use a different mountpoint (like a ramdisk, or a different drive) then you may want to set this variable to map the volume to your docker container.

# PaaS mode

Contentosd now supports a PaaS mode (platform as a service) that currently works with Amazon's Elastic Beanstalk service. It can be launched using the following environment variables:

* `USE_PAAS` - if set to true, contentosd will launch in a format that works with AWS EB. Containers will exit upon failure so that they can be relaunched automatically by ECS. This mode assumes `USE_WAY_TOO_MUCH_RAM` and `USE_FULL_WEB_NODE`, they do not need to be also set.
* `S3_BUCKET` - set this to the name of the S3 bucket where you will store shared memory files for contentosd in Amazon S3. They will be stored compressed in bz2 format with the file name `blockchain-$VERSION-latest.tar.bz2`, where $VERSION is the release number followed by the git short commit hash stored in each docker image at `/etc/contentosdversion`.
* `SYNC_TO_S3` - if set to true, the node will function to only generate shared memory files and upload them to the specified S3 bucket. This makes fast deployments and autoscaling for contentosd possible.

# Seed Nodes

A list of some seed nodes to get you started can be found in
[doc/seednodes.txt](doc/seednodes.txt).

This same file is baked into the docker images and can be overridden by
setting `CONTENTOSD_SEED_NODES` in the container environment at `docker run`
time to a whitespace delimited list of seed nodes (with port).

# Testing

See [doc/testing.md](doc/testing.md) for test build targets and info
on how to use lcov to check code test coverage.

# System Requirements

For a full web node, you need at least 270GB of disk space available. Contentosd uses a memory mapped file which currently holds 189GB of data and by default is set to use up to 215GB. The block log of the blockchain itself is a little over 48GB. It's highly recommended to run Contentosd on a fast disk such as an SSD or by placing the shared memory files in a ramdisk and using the `--shared-file-dir=/path` command line option to specify where. At least 16GB of memory is required for a full web node. Seed nodes (p2p mode) can run with as little as 4GB of memory with a 24 GB state file. Any CPU with decent single core performance should be sufficient. Contentosd is constantly growing. As of December 2017, these numbers were accurate, but you may find you need more disk space to run a full node. We are also constantly working on optimizing Contentos's use of disk space.

On Linux use the following Virtual Memory configuration for the initial sync and subsequent replays. It is not needed for normal operation.

```
echo    75 | sudo tee /proc/sys/vm/dirty_background_ratio
echo  1000 | sudo tee /proc/sys/vm/dirty_expire_centisec
echo    80 | sudo tee /proc/sys/vm/dirty_ratio
echo 30000 | sudo tee /proc/sys/vm/dirty_writeback_centisec
``
    )"};
};

BOOST_FIXTURE_TEST_SUITE( vm_test, Article )

BOOST_AUTO_TEST_CASE(zlib_test)
{
    std::stringstream buffer;
    std::string line;
    std::getline( input, line );
    while( input.good() )
    {
        buffer << line << "\n";
        std::string compressed = fc::zlib_compress( line );
        std::string decomp = fc::zlib_decompress( compressed );
        BOOST_CHECK_EQUAL( decomp, line );

        std::getline( input, line );
    }

    line = buffer.str();
    std::string compressed = fc::zlib_compress( line );
    std::string decomp = fc::zlib_decompress( compressed );
    BOOST_CHECK_EQUAL( decomp, line );
}

BOOST_AUTO_TEST_CASE(zlib_decomp_exception_data_test)
{
    std::string compressed{"000000000000000"};
    std::string decomp = fc::zlib_decompress( compressed );
    BOOST_CHECK_EQUAL( decomp, "" ); 
}

BOOST_AUTO_TEST_CASE(zlib_decomp_zero_data_test)
{
    std::string compressed{"\0\0\0\0"};
    std::string decomp = fc::zlib_decompress( compressed );
    BOOST_CHECK_EQUAL( decomp, "" ); 
}

BOOST_AUTO_TEST_CASE(zlib_modity_compressed_result_test)
{
    std::string uncompressed{"# System Requirements"};
    std::string compressed = fc::zlib_compress( uncompressed ); 
    compressed += "0123123123";
    std::string decomp = fc::zlib_decompress( compressed );
    std::cout << decomp << std::endl;
    BOOST_CHECK_EQUAL( decomp, uncompressed ); 
}

BOOST_AUTO_TEST_SUITE_END()
#endif