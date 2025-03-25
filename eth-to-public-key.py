#eff415edb6331f4f67bdb7f1ecc639da9bcc0550b100bb275c7b5b21ce3a7804

from eth_keys import keys
from eth_utils import to_checksum_address

private_key_hex = "eff415edb6331f4f67bdb7f1ecc639da9bcc0550b100bb275c7b5b21ce3a7804"
private_key = keys.PrivateKey(bytes.fromhex(private_key_hex))

public_key = private_key.public_key
address = to_checksum_address(public_key.to_address())

print("Ethereum Address:", address)
