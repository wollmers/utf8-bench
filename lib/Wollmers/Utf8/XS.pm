package Wollmers::Utf8::XS;

use 5.010;
use strict;
use warnings;

use utf8;

our $VERSION = '0.01';

#require XSLoader;
#XSLoader::load('Wollmers::Utf8::XS', $VERSION);

require Exporter;
require DynaLoader;
use Autoloader;

our @ISA = qw(Exporter DynaLoader);
our @EXPORT = qw( jb_chars cp_chars sc_chars );
bootstrap Wollmers::Utf8::XS $VERSION;


1;

__END__

=head1 NAME

Wollmers::Utf8::XS - Fast support of UTF-8

=head1 SYNOPSIS

  use utf8; # literals are in UTF-8
  use Wollmers::Utf8::XS;

  my $characters = '';


=head1 DESCRIPTION

=head2 CONSTRUCTOR

=over 4

=item new()

Creates a new object which maintains internal storage areas
for the computation.  Use one of these per concurrent
call.

=back

=head2 METHODS

=over 4

=item jb_chars($string)

Uses lookup table for calculating the number of characters.

=item cp_chars($string)

Uses lookup table.

Calculates

=back

=head2 EXPORT

None by design.

=head1 STABILITY

Until release of version 1.00 the included methods, names of methods and their
interfaces are subject to change.

Beginning with version 1.00 the specification will be stable, i.e. not changed between
major versions.

=head1 SEE ALSO

XXX

=head1 BUGS

Does not XXX.

=head1 AUTHOR

Helmut Wollmersdorfer E<lt>helmut.wollmersdorfer@gmail.comE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2022 by Helmut Wollmersdorfer

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=cut
