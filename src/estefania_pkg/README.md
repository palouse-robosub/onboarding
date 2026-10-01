# estefania_pkg

This package contains a publisher and subscriber.

The publisher publishes random `std_msgs/msg/Float32` values to the
`estefania_topic` topic at 0.5 Hz.

The subscriber listens to `estefania_topic`, summarizes the received
value, and sends the summary to the `echo_string` service.