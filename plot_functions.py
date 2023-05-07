import matplotlib.pyplot as plt

# Define the data for the three functions
blas = {
    400: 0.040290,
    500: 0.080949,
    600: 0.131025,
    700: 0.198116,
    800: 0.285428,
    900: 0.396836,
    1000: 0.561678,
    1100: 0.734086,
    1200: 0.934723,
    1300: 1.169696,
    1400: 1.431724,
    1500: 1.822059,
    1600: 2.179854
}

opt = {
    400: 0.368568,
    500: 0.713883,
    600: 1.231407,
    700: 1.942642,
    800: 2.904663,
    900: 4.118597,
    1000: 5.652847,
    1100: 7.523404,
    1200: 9.823234,
    1300: 12.547029,
    1400: 15.774285,
    1500: 19.510212,
    1600: 23.775011
}

neopt = {
    400: 1.118085,
    500: 2.190298,
    600: 3.891463,
    700: 5.948505,
    800: 9.445211,
    900: 12.603328,
    1000: 16.913977,
    1100: 22.865772,
    1200: 30.707788,
    1300: 43.487358,
    1400: 53.864227,
    1500: 72.666016,
    1600: 91.181343
}

# Create a figure and axes
fig, ax = plt.subplots()

# Plot the data for each function
ax.plot(blas.keys(), blas.values(), label='blas')
ax.plot(opt.keys(), opt.values(), label='opt')
ax.plot(neopt.keys(), neopt.values(), label='neopt')

# Add a title and axis labels
ax.set_title('Function Runtimes')
ax.set_xlabel('N')
ax.set_ylabel('Time (s)')

# Add a legend
ax.legend()

# Show the plot
plt.show()