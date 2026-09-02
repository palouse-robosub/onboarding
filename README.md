# Palouse RoboSub CS Onboarding

Getting new members up to speed with ROS development and our workflow!

## Your Task

You will add a package called `<your-name>_pkg` that publishes a topic of random message type (Float32, etc / see below) on a 0.5 Hz timer. You will also subscribe to that same topic, and summarize it into a string with your name. Next you'll publish that to the central `echo_service` node. In the end it will look cool with everyone's names and summaries like below:

```
root@1689cc4c21d7:/workspaces/onboarding# ros2 launch onboarding all.xml
[echo_service-1] [INFO] [1788337433.134494635] [echo_service]: Echo request recieved: cole recieved a float: 32.45
[echo_service-1] [INFO] [1788337476.212902835] [echo_service]: Echo request recieved: andy recieved a green image
[echo_service-1] [INFO] [1788337476.212902835] [echo_service]: Echo request recieved: oliver's IMU is accelerating +X
[echo_service-1] [INFO] [1788337476.212902835] [echo_service]: Echo request recieved: ryden's joystick is drifting
[echo_service-1] [INFO] [1788337476.212902835] [echo_service]: Echo request recieved: adrian's CAN packet was recieved
# ... etc ...
```

You can choose any messages from:
- [std_msgs](https://docs.ros.org/en/ros2_packages/jazzy/api/std_msgs/)
- [sensor_msgs](https://docs.ros.org/en/ros2_packages/jazzy/api/sensor_msgs/)
- [vision_msgs](https://docs.ros.org/en/ros2_packages/jazzy/api/vision_msgs/)
- [nav_msgs](https://docs.ros.org/en/ros2_packages/jazzy/api/nav_msgs/)
- or make your own! (super cool extension activity) See the `onboarding_msgs` package for an example...

---

1. Go through the introductory slides [here](https://docs.google.com/presentation/d/1zO_SN30oPfAyicZK6k94j2NxE_sYyuP0kzkFrnx4IoQ/edit?usp=sharing)
2. Get set up with the repo:
    1. [Create a GitHub account](https://github.com/signup/) and join the [palouse-robosub](https://github.com/palouse-robosub/) organization by pinging an admin on Discord
    2. [Install git](https://git-scm.com/) on your computer and clone this repo
    3. [Install Docker](https://www.docker.com/products/docker-desktop/) and enter the DevContainer by clicking the `><` symbol in the lower left of VS Code and clicking Reopen In Container.
3. Get ready to add changes:
    1. Create a new branch in the format `<your-name>/<what-you-are-adding>` (like `bob/add-bob-pkg`)
    2. Build the existing code by using `colcon build`
    3. Run the existing code with `ros2 launch onboarding all.xml`
    4. Make a copy of the `onboarding_example` package and name it `<your-name>_pkg`. Be sure to update all instances of the package name, even in files like `CMakeLists.txt`
4. Read the [ROS2 Jazzy Quickstart Tutorial](https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html#write-the-publisher-node) and:
    1. Create a publisher node that publishes your topic of choice on a 0.5Hz timer
    2. Update `CMakeLists.txt` and `package.xml`
    3. Create a subscriber node that summarizes the topic of your choice into a string of some sort
    4. Update `CMakeLists.txt` and `package.xml`
    5. Update your subscriber node to call the `/echo_string` service with your description string and name
    6. Update your launch file, and the one in `src/onboarding/`
5. Get ready to merge:
    1. Make sure your code is formatted properly by running `./util/format` in your terminal
    2. Build and run your code using `colcon ...` and `ros2 ...`
    3. Commit your changes & push them to GitHub
    4. Add your name to the `.github/CODEOWNERS` file!
6. [Open a Pull Request](https://github.com/palouse-robosub/onboarding/compare) and request review
    1. Ensure that CI passes
    2. Make any necessary changes
    3. Merge your first PR!
7. Celebrate 🎉🎉🎉

## Repo Setup

This repo was copied directly from [palouse-robosub/guppy](https://github.com/palouse-robosub/guppy/) in order to almost directly match its structure and function. Some notable features include:

- ROS Packages source code located in [src/](./src)
- Nix Flake at [flake.nix](./flake.nix) containing dependencies and a custom development environment
- [Dockerfile](./Dockerfile) which builds a DevContainer for local ROS development
- Custom [.clang-format](./.clang-format) file allowing standardized C++ formatting in `ryden-format`
- Preconfigured VSCode settings in [.vscode](./.vscode) with recommended extensions, autocompletion paths, and build settings
- CI/CD pipeline at [.github/workflows/ci.yaml](./.github/workflows/ci.yaml) that runs automatically on every push to lint, build, and test new code
- Codeowners file at [.github/CODEOWNERS](./.github/CODEOWNERS) allowing for automatic PR review requests, and keeping contributors updated about relevant changes

Each of these items was ported from `guppy` with minimal modification in order to replicate our actual development workflow. We would like you to become familiar and comfortable with all of the above tooling and practices.
