SKETCH := hitbox
FQBN := arduino:avr:leonardo

.PHONY: build
build:
	arduino-cli compile -b "$(FQBN)" "$(SKETCH)"

.PHONY: upload
upload: build
	$(eval PORT := $(shell arduino-cli board list --format json | jq '.[] | select(.matching_boards[]?.fqbn == "arduino:avr:leonardo") | .port.address' | tr -d '"'))
	arduino-cli upload -p "$(PORT)" -b "$(FQBN)" "$(SKETCH)"
