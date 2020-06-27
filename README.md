# READY: A Fine-Grained Multithreading Overlay Framework for Modern CPU-FPGA Dataflow Applications

In this work, we propose a framework called REconfigurable Accelerator DeploY (READY), the first framework to support polynomial runtime mapping of dataflow applications in high-performance CPU-FPGA platforms. READY introduces an efficient mapping with fine-grained multithreading onto an overlay architecture
that hides the latency of a global interconnection network. In addition to our overlay architecture, we show
how this system helps solve some of the challenges for FPGA cloud computing adoption in high-performance
computing. The framework encapsulates dataflow descriptions by using a target independent, high-level API,
and a dataflow model that allows for explicit spatial and temporal parallelism. READY directly maps the
dataflow kernels onto the accelerator. Our tool is flexible and extensible and provides the infrastructure to
explore different accelerator designs. We validate READY on the Intel Harp platform, and our experimental results show an average 2x execution runtime improvement when compared to an 8-thread multi-core
processor

# Publication

Lucas Bragança , Ricardo Ferreira, Michael Canesche, Marcelo M Menezes, Maria D Vieira, Jeronimo Penha, Peter Jamieson, José Augusto M Nacif, [READY: A Fine-Grained Multithreading Overlay Framework for Modern CPU-FPGA Dataflow Applications](https://dl.acm.org/doi/pdf/10.1145/3358187) in ACM Transactions on Embedded Computing System 2019.
  
If you find FDAM useful or if you use it in your work, please cite the following paper:
  
  ```
@article{ready,
  title={READY: A Fine-Grained Multithreading Overlay Framework for Modern CPU-FPGA Dataflow Applications},
  author={Silva, Lucas Bragan{\c{c}}a Da and Ferreira, Ricardo and Canesche, Michael and Menezes, Marcelo M and Vieira, Maria D and Penha, Jeronimo and Jamieson, Peter and Nacif, Jos{\'e} Augusto M},
  journal={ACM Transactions on Embedded Computing Systems (TECS)},
  volume={18},
  number={5s},
  pages={1--20},
  year={2019},
  publisher={ACM New York, NY, USA}
}

```
