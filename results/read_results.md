class: center, middle

# Performance Results

All tests below are averaged over 6 runs

.bottom[
[Start slideshow](https://tripu.github.io/remark/remarkise?url=https://github.com/OwenArnold/hdf5_vs_nexus/blob/master/results/read_results.md) generated with [Remark](https://github.com/gnab/remark)]]

---

# Owen's runs


| file/instrument        | info           | with nexus/ms  | with hdf5/ms
| ------------- |:-------------:| -----:|-----:|
| INTER      | Histogram, 5 * 1000 |3 | 2|
| POLREF      | Histogram, 246 * 1000      |   15 | 15 |
| POLREF | Histogram 641 * 1000   |  39   | 40|
| MARI | Histogram 922 * 2663    |  111   | 111 |

---

# Pete's machine

| file/instrument        | info           | with napi/ms  | with nexus/ms | with hdf5/ms
| ------------- |:----------------------:| -----:| -----:| -----:|
| INTER         | Histogram, 5 * 1000    | 4 |  3  | 2 |
| POLREF        | Histogram, 246 * 1000  |  22  | 19 | 22 |
| POLREF        | Histogram 641 * 1000   |  49  | 47 | 46 |
| MARI          | Histogram 922 * 2663   |  142   | 136 | 139 |
