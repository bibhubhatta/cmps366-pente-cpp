#include <string>

/// \brief Represents a position on the board
class Position

{
  public:
    /// \brief Creates a Position from a string of the form
    /// "<col_char><row_int>"
    /// \param position_string
    /// \return Position
    static Position from_string(const std::string& position_string);

    /// \brief Represents a position on the board
    /// \param row
    /// \param col
    Position(int row, int col);

    const int row;
    const int col;

    std::string to_string() const;

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

  private:
    static int get_row_number_from_position_string(const std::string& position);
    static int get_col_number_from_position_string(const std::string& position);
};
