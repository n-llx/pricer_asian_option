# Pricer Asian Option

## Project Description
This C++ open-source project prices path-dependent Asian options using Monte Carlo simulations. It models underlying asset paths via Geometric Brownian Motion to calculate arithmetic averages, delivering efficient derivative valuation through modern OOP principles and high-performance stochastic modeling.

The application supports:
- **Manual Mode**: User manual entry of option parameters (Spot, Volatility, Rate, etc.).
- **Automatic Mode**: Fetches real-time market data (Spot price, Historical Volatility) from Yahoo Finance for a given stock ticker.
- **Greeks Calculation**: Computes Delta, Vega, Gamma, Rho, and Theta.
- **Surface Plotting**: Visualizes price sensitivity using 3D surfaces via Gnuplot.

## How to Compile and Run

The project is designed to be portable and includes a local MinGW compiler and Gnuplot distribution for Windows.

### Windows
Simply execute the batch script:
```cmd
run_project.bat
```
This script will:
1.  Setup the environment (paths to compiler and Gnuplot).
2.  Compile the source code.
3.  Launch the application `pricer.exe`.

### macOS
1.  Open a terminal and navigate to the project folder.
2.  Make the script executable:
    ```bash
    chmod +x run_project.sh
    ```
3.  Run the script:
    ```bash
    ./run_project.sh
    ```

## Project Report
The detailed project report, containing the mathematical methodology, architecture decisions, and results, is located in the root directory of this repository:
`rapport.pdf`
