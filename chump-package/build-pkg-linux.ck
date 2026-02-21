@import "Chumpinate"

"1.0.0" => string version;

<<< "Generating Chumpinate package version " >>>;

Package pkg("Chumbi");

"Everett M. Carpenter" => pkg.authors;

"https://github.com/everettmcarpenter/Encode-Decode.chug" => pkg.homepage;
"https://github.com/everettmcarpenter/Encode-Decode.chug" => pkg.repository;

"MIT" => pkg.license;
"A Chump package designed for the creation of ambisonic architectures in ChucK. Meant for encoding, decoding and altering B-Format ambisonic signals, but misuse is always welcome." => pkg.description;

["ambisonics", "chugins", "spatialization", "multichannel"] => pkg.keywords;

"./" => pkg.generatePackageDefinition;

<<< "Defining version " + version >>>;

PackageVersion vers("Chumbi", version);

"10.2" => vers.apiVersion;

"1.5.4.0" => vers.languageVersionMin;

"linux" => vers.os;
"x86_64" => vers.arch;

vers.addFile("../current-builds/linux/Encode.chug");
vers.addFile("../current-builds/linux/Decode.chug");
vers.addFile("../current-builds/linux/SADN.chug");
vers.addFile("../current-builds/linux/OrderGain.chug");
vers.addFile("../current-builds/linux/Mirror.chug");
vers.addFile("../current-builds/linux/ABFormat.chug");
vers.addFile("../current-builds/linux/BAFormat.chug");

vers.addExampleFile("examples/basic/encode.ck");
vers.addExampleFile("examples/basic/simple-decode.ck");
vers.addExampleFile("examples/deep/advanced-decode.ck");

vers.addDocsFile("doc/index.html");
vers.addDocsFile("doc/decoders.html");
vers.addDocsFile("doc/encoders.html");
vers.addDocsFile("doc/utilities.html");

"Chumbi/" + vers.version() + "/" + vers.os() + "/Chumbi.zip" => string path;

<<< path >>>;

vers.generateVersion("./", "Chumbi-"+vers.os(), "https://everettmiles.com/" + path);

chout <= "Use the following commands to upload the package to CCRMA's servers:" <= IO.newline();
chout <= "ssh nshaheed@ccrma-gate.stanford.edu \"mkdir -p ~/Library/Web/chugins/Chumpinate/"
      <= vers.version() <= "/" <= vers.os() <= "\"" <= IO.newline();
chout <= "scp Chumpinate_windows.zip nshaheed@ccrma-gate.stanford.edu:~/Library/Web/" <= path <= IO.newline();

vers.generateVersionDefinition("Chumbi-"+vers.os(), "./" );

chout <= IO.nl();