# LaserDiodeStabilizer
C/C++ code for feedback voltage control of laser diode outputs with a microcomputer, STM32L152RE. Two AD channels of it recieve command and feedback voltages, and positive and negative correction voltages are the delivered via two DA channels. Information of a practical circuit  is available here (https://figshare.com/articles/LaserDiodeStabilizerCircuit/5419195).

## Getting Started

### Prerequisites
* Microcomputer STM32L152RE (http://www.st.com/en/microcontrollers/stm32l152re.html)

### How to use
* Online compile and downlowad
1. Connect your Nucleo and PC with an USB cable.
2. Compile the code and download binary file to your Nucleo directly via mbed webpage (https://os.mbed.com/compiler/).

* Offline compile and download
1. Install an offline developmental environment, Keil uVision 5 (http://www2.keil.com/mdk5/uvision/).
2. Export mbed libraries as uVision project from mbed homepage.
4. Connect your Nucleo and PC with an USB cable.
3. Compile and download your code in uVision 5.

## DOI
[![DOI](https://zenodo.org/badge/104104021.svg)](https://zenodo.org/badge/latestdoi/104104021)

## Versioning
We use [SemVer](http://semver.org/) for versioning.

## Releases
* Ver 1.0.0, 2017/09/20: The first release.
* Pre-release, 2017/09/19.

## Authors
* **Yuichi Takeuchi PhD** - *Initial work* - [GitHub](https://github.com/yuichi-takeuchi)
* Affiliation: Department of Physiology, University of Szeged, Hungary

## License
This project is licensed under the MIT License.

## Acknowledgments
* The Uehara Memorial Foundation
* Department of Physiology, University of Szeged, Hungary


## References
- Takeuchi Y, Harangozó M, Pedraza L, Földi T, Kozák G, Li Q, Berényi A, Closed-loop stimulation of the medial septum terminates epileptic seizures. Brain, awaa450. 27 Jan 2021. DOI: https://doi.org/10.1093/brain/awaa450
