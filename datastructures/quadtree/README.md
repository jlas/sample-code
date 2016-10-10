# quadtree

Basic quadtree based on [this](https://en.wikipedia.org/wiki/Quadtree#Pseudo_code)


To test it, start with a dataset in .csv format e.g.:

    0.813770463931,-0.148110910624,0.0610378728183
    -0.174801629674,0.88305156427,-0.239274764111
    -1.33901594528,0.549597887275,-0.664989888538
    -0.402022489688,1.46607711446,2.33411672811
    0.421355865864,1.10349755402,-1.41511921999
    ...

Then build and run:

    make
    cat data.csv | ./quadtree > out.ppm
    display out.ppm