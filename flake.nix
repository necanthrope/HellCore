{
  description = "The HellCore MOO engine and database.";

  # Flake compatibility functions.
  inputs.flake-compat = {
    url = "github:edolstra/flake-compat";
    flake = false;
  };

  # Flake utility functions.
  inputs.flake-utils.url = "github:numtide/flake-utils";

  # The outputs this flake provides.
  outputs =
    { self
    , nixpkgs
    , flake-utils
    , ...
    }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      # The packages we use to provide gcc, etc.
      pkgs = import nixpkgs {
        inherit system;
      };
    in
    rec {
      # The contents of a shell for developing on hellcore.
      devShell = pkgs.mkShell {
        # Include all the dependencies of hellcore in the shell, to allow easy
        # manual building.
        inputsFrom = [
          packages.hellcore
        ];
      };

      # The default package to build.
      defaultPackage = packages.hellcore;

      packages = flake-utils.lib.flattenTree {
        # The hellcore package.
        hellcore = pkgs.stdenv.mkDerivation rec {
          # The package name, version, and full package-version for this
          # hellcore build.
          pname = "hellcore";
          version = self.lastModifiedDate;
          name = "${pname}-${version}";

          src = self;

          # The build-time inputs needed to build hellcore.
          nativeBuildInputs = with pkgs; [
            # This automatically regenerates the autoconf and automake build
            # system.
            autoreconfHook

            # The bison parser generator.
            bison

            # The flex lexxer generator.
            flex

            # The gperf perfect hash generator for recognizing keywords.
            gperf
          ];

          # Extra flags to pass to ./configure.
          configureFlags = [
            # Show the full compiler calls, rather than just CC <file> for
            # logging.
            "--disable-silent-rules"
          ];
        };
      };
    }
    );
}
