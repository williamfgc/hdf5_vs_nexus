class: center, middle

# Performance Results

All tests below are averaged over 6 runs

.bottom[
[Start slideshow](https://gnab.github.io/remark/remarkise?url=https://github.com/OwenArnold/hdf5_vs_nexus/blob/master/results/read_results.md) generated with [Remark](https://github.com/gnab/remark)]

---

# Owen's runs


| file/instrument        | info           | with nexus (napi)/ms  | with hdf5/ms
| ------------- |:-------------:| -----:|-----:|
| INTER      | Histogram, 5 * 1000 |3 | 2|
| POLREF      | Histogram, 246 * 1000      |   15 | 15 |
| POLREF | Histogram 641 * 1000   |  39   | 40|
| MARI | Histogram 922 * 2663    |  111   | 111 |

---

# Pete's machine

| file/instrument  | info                | with nexus (c++)/ms | with nexus (napi)/ms | with hdf5/ms
| ------------- |:----------------------:| -------------------:| ---:| -----:|
| INTER         | Histogram, 5 * 1000    |   3                 |   4 |   2.0&plusmn;.4 |
| POLREF        | Histogram, 246 * 1000  |  19                 |  22 |  21&plusmn;4 |
| POLREF        | Histogram 641 * 1000   |  47                 |  49 |  49&plusmn;3 |
| MARI          | Histogram 922 * 2663   | 136                 | 142 | 144&plusmn;5 |
| SEQ_12345     |                        | 472&plusmn;4        |     | 183&plusmn;6 |
| PG3_12345     |                        | 380&plusmn;10       |     | 356&plusmn;2 |
| NOM_12345     |                        | 291&plusmn;8        |     |  41&plusmn;3 |

---

# Comments on the differences

1. There does not appear to be a huge difference for the histogram case (equivalent of `LoadNexusProcessed`)
2. HDF5's c-api is really cumbersome, but has some nice features
3. The [nexus-c++](http://download.nexusformat.org/doxygen/html-cpp/index.html) example is a near identical to what is being done in `LoadEventNexus`. The HDF5-c example is very different.
4. Further investigation into using [HDF5-C++](http://www.hdfgroup.org/HDF5/doc/cpplus_RM/index.html) are suggested as it already comes with existing packages
