#include <iostream>

// node of linked list
class PolyNode
{
public:
    int coefficient;
    int exponent;
    PolyNode *next;
    PolyNode(int coefficient, int exponent) : coefficient(coefficient), exponent(exponent), next(NULL) {}
};

class Poly
{
public:
    PolyNode *head;

    Poly() : head(NULL) {}
    Poly(const Poly &poly){
        if (poly.head == NULL)
        {
            this->head = NULL;
            return;
        }

        PolyNode *temp = poly.head;
        this->head = new PolyNode(temp->coefficient, temp->exponent);
        PolyNode *tail = this->head;
        while (temp->next != NULL){
            temp = temp->next;
            tail->next = new PolyNode(temp->coefficient, temp->exponent);
            tail = tail->next;
        }
    }
    Poly(int coefficient, int exponent) : head(new PolyNode(coefficient, exponent)) {}
    // Poly(const Poly &poly) : head(poly.head) {}
    Poly(PolyNode *node) : head(node) {}
    // ~Poly()
    // {
    //     PolyNode *temp = head;
    //     while (temp!= NULL)
    //     {
    //         PolyNode *temp2 = temp->next;
    //         delete temp;
    //         temp = temp2;
    //     }
    // }

    friend std::ostream &operator<<(std::ostream &output, const Poly &poly);

    // template <typename T>
    // Poly operator+(T &&polynode) const{
    Poly operator+(PolyNode &&polynode) {

        if (this->head == NULL)
        {
            return Poly(&polynode);
        }

        if (polynode.exponent > this->head->exponent)
        {
            polynode.next = this->head;
            this->head = &polynode;
            return *this;
        }

        PolyNode *node_ptr = this->head;
        PolyNode *prev_node_ptr = NULL;


        while (node_ptr != NULL &&
                polynode.exponent < node_ptr->exponent)
        {
            prev_node_ptr = node_ptr;
            node_ptr = node_ptr->next;
        }

        if (node_ptr != NULL &&
            polynode.exponent == node_ptr->exponent)
        {
            node_ptr->coefficient += polynode.coefficient;
            if (node_ptr->coefficient == 0)
            {
                if (this->head == node_ptr)
                {
                    this->head = node_ptr->next;
                }
                else
                {
                    prev_node_ptr->next = node_ptr->next;
                }
                delete node_ptr;
            }
        }
        else
        {
            prev_node_ptr->next = &polynode;
            polynode.next = node_ptr;
        }
        return *this;
    }

    Poly operator+=(PolyNode &polynode){
        return *this + std::move(polynode);
    }

    // Poly operator+(Poly &poly){
    template <typename T>
    Poly operator+(T &&poly){
        if (this->head == NULL)
        {
            return poly;
        }

        while (poly.head != NULL)
        {
            PolyNode *node = poly.head;
            poly.head = poly.head->next;
            *this += *node;
        }
        return *this;

    }

    Poly operator*(PolyNode &&node){
        PolyNode *temp = this->head;
        if (node.coefficient == 0)
        {
            while (temp != NULL)
            {
                PolyNode *prev = temp;
                temp = temp->next;
                delete prev;
            }
            this->head = NULL;
            return *this;
        }


        while (temp!= NULL){
            if (temp->coefficient == 0)
            {
                if (temp == this->head)
                {
                    this->head->coefficient = 0;
                    this->head->exponent = 0;
                    temp = temp->next;
                }
                else{
                    PolyNode *prev = temp;
                    temp = temp->next;
                    delete prev;
                }
            }
            else
            {
                temp->coefficient *= node.coefficient;
                temp->exponent += node.exponent;
                temp = temp->next;
            }
        }
        return *this;
    }

    Poly operator*=(PolyNode &polynode){
        return *this * std::move(polynode);
    }

    // Poly operator*(Poly &poly){
    template <typename T>
    Poly operator*(T &&poly){
        Poly ret;
        PolyNode *node = poly.head;
        while (node!= NULL)
        {
            Poly temp(*this);
            temp *= *node;
            ret = ret + temp;
            node = node->next;
        }

        //delete this poly
        node = this->head;
        PolyNode *prev = node;
        while (node!= NULL){
            prev = node;
            node = node->next;
            delete prev;
        }

        return ret;
    }
};

// print Poly
std::ostream &operator<<(std::ostream &output, const Poly &poly)
{
    PolyNode *temp = poly.head;
    if (temp == NULL)
    {
        output << "0";
    }

    while (temp!= NULL)
    {
        if (temp->coefficient < 0)
        {
            output << temp->coefficient << "x^" << temp->exponent << " ";
        }
        else if (temp->coefficient == 0)
        {
            output << temp->coefficient << " ";
        }
        else if (temp == poly.head)
        {
            output << temp->coefficient << "x^" << temp->exponent << " ";
        }
        else
        {
            output << " +" << temp->coefficient << "x^" << temp->exponent << " ";
        }
        temp = temp->next;
    }
    return output;
}


int main()
{
    Poly p1 = Poly(0,0);
    Poly p2 = Poly(1,2) + PolyNode(1,1) + PolyNode(1,0);
    std::cout << Poly(p1) + Poly(p2) << std::endl;
    std::cout << Poly(p1) * Poly(p2) << std::endl;

    p1 = Poly(3,5) + PolyNode(1,1) + PolyNode(1,1);
    p2 = Poly(-2,1) + PolyNode(1,2);
    std::cout << Poly(p1) + Poly(p2) << std::endl;
    std::cout << Poly(p1) * Poly(p2) << std::endl;

    p1 = Poly(5,1) + PolyNode(-7,0);
    p2 = Poly(-5,1) + PolyNode(7,0);
    std::cout << Poly(p1) + Poly(p2) << std::endl;
    std::cout << Poly(p1) * Poly(p2) << std::endl;

    return 0;
}