# This file helps set up all the dependencies for running on your computer!

{
  inputs = {
    nix-ros-overlay.url = "github:lopsided98/nix-ros-overlay/master";
    nixpkgs.follows = "nix-ros-overlay/nixpkgs";  # IMPORTANT!!!

    nixpkgs-unstable.url = "github:nixos/nixpkgs/nixos-unstable";
  };
  outputs = { self, nix-ros-overlay, nixpkgs, nixpkgs-unstable }:
    nix-ros-overlay.inputs.flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ nix-ros-overlay.overlays.default ];
        };

	unstable = import nixpkgs-unstable { inherit system; };
      in {
        devShells.default = pkgs.mkShell {
          name = "onboarding_ros";
          packages = [
            # non ros
            
            # build
            pkgs.colcon
            pkgs.cmake
            pkgs.clang-tools
            
            # deps
            (unstable.python3.withPackages (ps: with ps; [
              pip
            ]))

            # extra
            pkgs.fastfetch
            pkgs.can-utils
            
            (with pkgs.rosPackages.jazzy; buildEnv {
              # ros packages
              paths = [
                # ros base
                ros-core
                ros-base
                rclcpp
                rclpy
                
                # ros msgs
                std-msgs
                geometry-msgs
                sensor-msgs
                nav-msgs
      
                # build
                ament-cmake
                ament-cmake-core # vectornav_msgs
                ament-cmake-python
                ament-lint-auto
                python-cmake-module
                
                # launch
                launch
                launch-ros
                launch-xml
              ];
            })
          ];
          # shellHook = ''
          #   fastfetch -l ./.github/onboarding.txt
          # '';
        };
      });
  nixConfig = {
    extra-substituters = [ "https://ros.cachix.org" "https://palouse-robosub.cachix.org" ];
    extra-trusted-public-keys = [ "ros.cachix.org-1:dSyZxI8geDCJrwgvCOHDoAfOm5sV1wCPjBkKL+38Rvo=" "palouse-robosub.cachix.org-1:r2KNmfNGOZB+IhqEqDIMDaEWMYZv8ct1tdSg7n7fNKw=" ];
  };
}
