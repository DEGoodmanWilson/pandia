# pandia

The ridonculously fast local file server.

## Wat?

- You're building a static website, and you need to preview your work in the broswer. You want a stupid fast server to dish out those files with a quickness. Just run `pandia` in your working folder, the browser to [http://localhost:8273](http://localhost:8273)

- You want to share some files from your computer to the world. Just run `pandia` in the folder you want to share, then use something like [ngrok](https://ngrok.com/) or [smee](https://smee.io/) to let the outside world in.

## Installing

At the moment, only MacOS is supported for quick installation. Other platforms can compile from source.

```bash
brew install degoodmanwilson/tools/pandia
```

## Compiling

Requires [conan](https://conan.io/), cmake, and a modern compiler.

```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add vthiery https://api.bintray.com/conan/vthiery/conan-packages
conan remote add DEGoodmanWilson https://api.bintray.com/conan/degoodmanwilson/opensource
conan install . --build=missing
cmake .
cmake --build .
cp ./bin/pandia /usr/local/bin/whatever/doesn\'t_matter/
```