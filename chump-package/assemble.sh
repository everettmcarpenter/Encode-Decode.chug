# documentation generation (nice)
chuck doc/make-doc.ck

# linux (easiest)
chuck -s build-pkg-linux.ck

# windows
chuck -s build-pkg-win.ck

# mac
./1-codesign.sh
chuck -s build-pkg-mac.ck
./3-notarize.sh