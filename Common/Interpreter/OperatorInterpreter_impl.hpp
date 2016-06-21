
NAMESPACE_BEGIN(interp)

    UNARY_OP_IMPL( SizeOperator, size, # )
    UNARY_OP_IMPL( UnaryMinusOperator, minus, - )
    UNARY_OP_IMPL( NotOperator, not_, ! )

    BINARY_OP_IMPL( ConcatOperator, concat, & )
    BINARY_OP_IMPL( PlusOperator, plus, + )
    BINARY_OP_IMPL( MinusOperator, minus, - )
    BINARY_OP_IMPL( MultiplyOperator, multiply, * )
    BINARY_OP_IMPL( DivideOperator, divide, / )
    BINARY_OP_IMPL( EqualOperator, equals, == )
    BINARY_OP_IMPL( NotEqualOperator, notEquals, != )
    BINARY_OP_IMPL( IEqualOperator, iequals, =~ )
    BINARY_OP_IMPL( NotIEqualOperator, notIEquals, !~ )
    BINARY_OP_IMPL( InferiorOperator, inferior, < )
    BINARY_OP_IMPL( InferiorOrEqualOperator, inferiorOrEqual, <= )
    BINARY_OP_IMPL( SuperiorOperator, superior, > )
    BINARY_OP_IMPL( SuperiorOrEqualOperator, superiorOrEqual, >= )
    BINARY_OP_IMPL( AndOperator, and_, && )
    BINARY_OP_IMPL( OrOperator, or_, || )
    BINARY_OP_IMPL_REF( LoadOperator, load, >> )
    BINARY_OP_IMPL( SaveOperator, save, << )

NAMESPACE_END

