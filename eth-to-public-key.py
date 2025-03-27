from eth_keys import keys
from eth_utils import to_checksum_address

private_key_hex = "6d79b9a9a0eb1d252859fd15a6287d4434b4926b7360650e0b3869e5e463f7d2"
private_key = keys.PrivateKey(bytes.fromhex(private_key_hex))

public_key = private_key.public_key
address = to_checksum_address(public_key.to_address())

print("Ethereum Address:", address)
