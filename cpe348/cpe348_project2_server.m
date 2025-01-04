% if existing valid server, then clear it
if exist('server', 'var') && isvalid(server)
    clear server;
end
% get hostname of local computer, trim whitespace, and convert to string
[~, hostname] = system("hostname");
hostname = string(strtrim(hostname));
% resolve hostname to an IP address
address = resolvehost(hostname, "address");
% create a TCP/IP server listening on specified IP address and port (5001)
server = tcpserver(address, 5001, ByteOrder="big-endian", ConnectionChangedFcn=@connectionFcn);
% connectionFcn called when the connection status of the TCP/IP server changes

function connectionFcn(src, ~)
    if src.Connected
        bit_sequence = [1 1 0 0 1 0 1 0 1];
        % nrz encoding is level based
        data = bit_sequence;
        % append the last bit to hold its value
        data = [data, bit_sequence(end)];
        % send data
        write(src, data, "double");
    end
end