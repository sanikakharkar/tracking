
tracks_straight = csvread("output_straight.csv");

figure(1);
ax1 = subplot(2,1,1);
plot(tracks_straight(:,1), -tracks_straight(:,2));
title("Location of the car over time");
xlabel("X position (meters)");
ylabel("Y position (meters)");
axis("equal")

ax2 = subplot(2,1,2);
plot(tracks_straight(:,3));
title("Velocity of the car over time");
xlabel("Time (seconds)");
ylabel("Velocity (meters/second)");

tracks_turning = csvread("output_turning.csv");

figure(2);
ax1 = subplot(2,1,1);
plot(tracks_turning(:,1), -tracks_turning(:,2));
title("Location of the car over time");
xlabel("X position (meters)");
ylabel("Y position (meters)");
axis("equal")

subplot(2,1,2);
ax2 = plot(tracks_turning(:,3));
title("Velocity of the car over time");
xlabel("Time (seconds)");
ylabel("Velocity (meters/second)");

