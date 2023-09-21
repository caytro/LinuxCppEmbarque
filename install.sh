#!/bin/sh

# compilation
echo "Entering devel/AIrQualityWAtch/"
cd devel/AIrQualityWAtch
echo "g++ -o ../../airQualityWatch main.cpp mycurl.cpp  myparsing.cpp myoptions.cpp mygraphics.cpp myregex.cpp -lcurl -lgd"
g++ -o ../../airQualityWatch-qemu main.cpp mycurl.cpp  myparsing.cpp myoptions.cpp mygraphics.cpp myregex.cpp -lcurl -lgd
echo "...done"
echo "Leaving devel/AIrQualityWatch/"
cd ../..
echo "./airQualityWatch to launch app"


