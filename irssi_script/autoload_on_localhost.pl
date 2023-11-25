use strict;
use Irssi;
use vars qw($VERSION %IRSSI);

$VERSION = "1.0";
%IRSSI = (
    name        => 'autoload_on_localhost',
    description => 'Auto-load a script on connecting to localhost',
);

sub on_server_connected {
    my ($server) = @_;
    if ($server->{address} eq 'localhost') {
        Irssi::command('script load custom_command.pl');
    }
}

Irssi::signal_add('server connected', 'on_server_connected');
