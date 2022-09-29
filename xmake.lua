add_requires("sokol")
add_requires("glm")
add_requires("stb")

add_rules("mode.debug", "mode.release")
add_requires("glfw")

includes("external/xmake_soloud.lua")
add_requires("soloud")

  target("engine")
      set_kind("static")
      set_languages("cxx17")

      -- Declare our engine's header path.
      -- This allows targets that depend on the engine to #include them.
      add_includedirs("src", {public = true})

      add_files("src/*.cpp")
      add_packages("glfw", {public = true})
      add_packages("soloud", {public = true})
      add_packages("sokol", {public = true})
      add_packages("glm")
      add_packages("stb", {public = true})

  target("helloworld")
      set_kind("binary")
      set_languages("cxx17")

      add_deps("engine")

      add_files("demo/helloworld.cpp")

      -- Copy assets
      after_build(function (target)
        cprint("Copying assets")
        os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
      end)

target("threadpool")
  set_kind("binary")
  set_languages("cxx17")
  add_includedirs("src", {public = true})

  add_files("demo/threadpool.cpp")
