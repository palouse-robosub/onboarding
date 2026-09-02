# Palouse RoboSub CS Onboarding

Getting new members up to speed with ROS development and our workflow!

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

## Your Task

1. [Create a GitHub account](https://github.com/signup/) and join the [palouse-robosub](https://github.com/palouse-robosub/) organization
2. [Install git](https://git-scm.com/) on your computer and clone the repo
3. Create a new branch in the format `<your-name>/<what-you-are-adding>`
4. [Install Docker](https://www.docker.com/products/docker-desktop/) and enter the DevContainer
5. Create a publisher node
6. Update `CMakeLists.txt` and `package.xml`
7. Create a subscriber node
8. Update `CMakeLists.txt` and `package.xml`
9. Update your subscriber node to call the `/echo_string` service
10. Update launch files
11. Commit your changes & push them to GitHub
12. [Open a Pull Request](https://github.com/palouse-robosub/onboarding/compare) and request review
13. Ensure that CI passes
14. Make any necessary changes
15. Merge your first PR!
16. Celebrate 🎉🎉🎉