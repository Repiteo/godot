def can_build(env, platform):
    return True


def configure(env):
    pass


def is_enabled():
    # Temporarily enable for all environments for one pass.
    return True

    # # The module is disabled by default. Use module_benchmark_enabled=yes to enable it.
    # return False
