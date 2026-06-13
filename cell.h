#ifndef CELL_H
#define CELL_H

class Cell{
private:
    bool flagged;
    int val;
    bool visible;

public:
    Cell();
    Cell(int i);
    Cell(const Cell &other);
    Cell& operator=(const Cell &other);

    bool is_mine() const;
    bool is_flagged()const;
    bool is_visible() const;   

    int get_val() const;

    void set_val(int i);
    void set_mine();
    void set_flag();
    void remove_flag();
    void make_visible();

    ~Cell() = default;
};

#endif