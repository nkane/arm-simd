.PHONY: help 
all: help

build-asm-no-optim: ## Build assembly file no optimizations
	clang -framework Accelerate -O0 -S intrinsics.c

build-binary-no-optim: ## Build binary file no optimizations
	clang -framework Accelerate -O0 -g -o intrinsics intrinsics.c

help: ## Display this help screen
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
