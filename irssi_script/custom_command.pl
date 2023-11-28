use strict;
use Irssi;

use vars qw($VERSION %IRSSI);

sub cmd_help {
    my ($args, $server, $win) = @_;
    redirect_command($server, "HELP", $args);
}

# sub cmd_names {
#     my ($args, $server, $win) = @_;
#     redirect_command($server, "NAMES", $args);
# }

sub redirect_command {
    my ($server, $command, $args) = @_;
    if ($server) {
        # Envoie la commande spécifiée au serveur
        $server->send_raw("$command $args");
        # Arrête le traitement par Irssi
        Irssi::signal_stop();
    } else {
        Irssi::print("Vous n'êtes pas connecté à un serveur.");
    }
}

Irssi::command_bind("help", "cmd_help");
Irssi::command_bind("names", "cmd_names");