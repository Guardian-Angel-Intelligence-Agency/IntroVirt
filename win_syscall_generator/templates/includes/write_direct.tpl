    os << std::{{ arg['writeBase'] }} << {{ '"0x" <<' if arg['writeBase'] == 'hex' }} {{arg['functionName']}}() << '\n';