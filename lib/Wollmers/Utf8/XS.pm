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
our @EXPORT = qw( distance simple distance_arr toucs);
bootstrap Wollmers::Utf8::XS $VERSION;


1;

__END__

=head1 NAME

Wollmers::Utf8::XS - Fast XXX

=head1 SYNOPSIS

  use Wollmers::Utf8::XS;


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

=item foo($a,$b)

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

Text::Levenshtein

=head1 BUGS

Does not compile on Windows and Sun.

=head1 AUTHOR

Helmut Wollmersdorfer E<lt>helmut.wollmersdorfer@gmail.comE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2022 by Helmut Wollmersdorfer

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=cut
