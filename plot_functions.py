import matplotlib.pyplot as plt

# Define the data for the three functions
blas = {
    400: 0.040512,
    500: 0.081174,
    600: 0.132254,
    700: 0.199691,
    800: 0.287245,
    900: 0.398964,
    1000: 0.566673,
    1100: 0.741773,
    1200: 0.940245,
    1300: 1.174512,
    1400: 1.439273,
    1500: 1.830243,
    1600: 2.188797
}

opt = {
    400: 0.291104,
    500: 0.549925,
    600: 1.608891,
    700: 3.565503,
    800: 2.268724,
    900: 3.194524,
    1000: 4.369854,
    1100: 5.512434,
    1200: 7.195324,
    1300: 9.529752,
    1400: 11.998105,
    1500: 15.678024,
    1600: 24.465864
}

neopt = {
    400: 1.115916,
    500: 2.180850,
    600: 3.882337,
    700: 5.935851,
    800: 9.266505,
    900: 12.521920,
    1000: 16.939447,
    1100: 23.407904,
    1200: 31.416428,
    1300: 43.221939,
    1400: 53.519012,
    1500: 72.440521,
    1600: 90.029343
}

# Define custom colors for each line
blas_color = '#0072B2'
opt_color = '#009E73'
neopt_color = '#D55E00'

# Define markers for each data point
marker_size = 8
blas_marker = 'o'
opt_marker = 's'
neopt_marker = 'D'

# Create a figure and axes
fig, ax = plt.subplots()

# Plot the data for each function
ax.plot(blas.keys(), blas.values(), marker=blas_marker, markersize=marker_size, linestyle='-', linewidth=2, color=blas_color, label='BLAS')
ax.plot(opt.keys(), opt.values(), marker=opt_marker, markersize=marker_size, linestyle='-', linewidth=2, color=opt_color, label='Optimized')
ax.plot(neopt.keys(), neopt.values(), marker=neopt_marker, markersize=marker_size, linestyle='-', linewidth=2, color=neopt_color, label='Not Optimized')

# Add a title and axis labels
ax.set_title('Matrix Multiplication Runtimes', fontsize=18)
ax.set_xlabel('Matrix Size (N)', fontsize=14)
ax.set_ylabel('Time (s)', fontsize=14)

# Set the font size for the title
ax.set_title('Comparison of Function Runtimes', fontsize=18)

# Add grid lines
ax.grid(True)

# Customize the x-axis ticks
ax.set_xticks([400, 600, 800, 1000, 1200, 1400, 1600])
ax.set_xticklabels(['400', '600', '800', '1000', '1200', '1400', '1600'], fontsize=12)

# Customize the y-axis ticks
ax.set_yticks([0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100])
ax.set_yticklabels(['0s', '5s', '10s', '15s', '20s', '25s', '30s', '35s', '40s', '45s', '50s', '1m', '1m 10s', '1m 20s', '1m 30s', '1m 40s'], fontsize=12)

# Add a legend and set its font size
ax.legend(fontsize=12)

# Show it
plt.show()