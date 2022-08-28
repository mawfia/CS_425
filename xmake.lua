add_rules("mode.debug", "mode.release")
add_requires("glfw")

  target("engine")
      set_kind("static")
      set_languages("cxx17")

      -- Declare our engine's header path.
      -- This allows targets that depend on the engine to #include them.
      add_includedirs("src", {public = true})

      add_files("src/*.cpp")
      add_packages("glfw")

  target("helloworld")
      set_kind("binary")
      set_languages("cxx17")

      add_deps("engine")

      add_files("demo/helloworld.cpp")
