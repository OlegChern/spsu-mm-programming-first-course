namespace AlgebraicCurveLibrary
{
    public abstract class CurveBase
    {
        #region fields
        private string name;
        private DrawableCurveType type;
        #endregion

        #region properties
        public string Name
        {
            get
            {
                return name;
            }
        }

        public DrawableCurveType Type
        {
            get
            {
                return type;
            }
        }
        #endregion

        public CurveBase(string name, DrawableCurveType type)
        {
            this.name = name;
            this.type = type;
        }

        public override string ToString()
        {
            return name;
        }
    }
}
