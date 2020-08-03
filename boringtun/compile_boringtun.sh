#install required tools
sudo apt-get update
sudo apt-get -y install build-essential python git ca-certificates wget curl zip unzip


#install rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

#exit and relogin
exit



#get 'gcc-arm-linux-gnueabihf' toolchain
sudo apt-get -y install gcc-arm-linux-gnueabihf

rustup target add armv7-unknown-linux-musleabihf



#clone
git clone https://github.com/cloudflare/boringtun
cd boringtun

#android /tmp is in /data/local/tmp
find ./ -type f -exec sed -i 's/\/tmp/\/data\/local\/tmp/g' {} \;
#

#https://users.rust-lang.org/t/static-cross-build-for-arm/9100/2
export CARGO_TARGET_ARMV7_UNKNOWN_LINUX_MUSLEABIHF_LINKER=arm-linux-gnueabihf-gcc
export CC_armv7_unknown_linux_musleabihf=arm-linux-gnueabihf-gcc

#now compile
CFLAGS="-fPIE -march=armv7-a -mfpu=vfpv3-d16" CXXFLAGS="-fPIE -march=armv7-a -mfpu=vfpv3-d16" \
	cargo build --bin boringtun --release --target armv7-unknown-linux-musleabihf
mkdir executables
cd executables
cp ../target/armv7-unknown-linux-musleabihf/release/boringtun .
cp boringtun boringtun-stripped
arm-linux-gnueabihf-strip boringtun-stripped

zip binaries.zip *

#done
echo "Done, output file is in binaries.zip"

