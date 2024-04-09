//
// Created by Anonymous on 2024/4/8.
//

#include "include/tab/recycling_test.hpp"

std::vector<Chain> recycling_test;
std::vector<Chain> current_chain;

RecyclerCellTest::RecyclerCellTest(std::string text)
{
    this->setFocusable(true);
    this->setPaddingLeft(75);
    this->setPaddingRight(75);
    this->label = new brls::Label();
    this->label->setText(text);
    this->addView(this->label);
}

RecyclerCellTest* RecyclerCellTest::create()
{
    return new RecyclerCellTest();
}

// DATA SOURCE

int TestDataSource::numberOfSections(brls::RecyclerFrame* recycler)
{
    return 1;
}

int TestDataSource::numberOfRows(brls::RecyclerFrame* recycler, int section)
{
    return current_chain.size();
}

std::string TestDataSource::titleForHeader(brls::RecyclerFrame* recycler, int section)
{
    if (section == 0)
        return "";
    return "Section #" + std::to_string(section+1);
}

brls::RecyclerCell* TestDataSource::cellForRow(brls::RecyclerFrame* recycler, brls::IndexPath indexPath)
{
    RecyclerCellTest* item = (RecyclerCellTest*)recycler->dequeueReusableCell("Cell");
    auto c = current_chain[indexPath.row];
    item->label->setText(c.text);
    return item;
}

void TestDataSource::didSelectRowAt(brls::RecyclerFrame* recycler, brls::IndexPath indexPath)
{
    auto c = current_chain[indexPath.row];
    current_chain = c.child;
    recycler->reloadData();
}

// RECYCLER VIEW

RecyclingTest::RecyclingTest()
{
    // Inflate the tab from the XML file
    this->inflateFromXMLRes("xml/tabs/recycling_list.xml");

    recycling_test.clear();
    recycling_test.push_back(Chain{
        .text = "Top1-1",
        .child = std::vector<Chain> {
            { .text = "Top1-1-1" },
        }
    });
    recycling_test.push_back(Chain{
        .text = "Top1-2",
        .child = std::vector<Chain> {
            { .text = "Top1-2-1" },
            { .text = "Top1-2-2" },
            { .text = "Top1-2-3" },
        }
    });
    recycling_test.push_back(Chain{
        .text = "Top1-3",
        .child = std::vector<Chain> {
            { .text = "Top1-3-1" },
        }
    });
    current_chain = recycling_test;

    recycler->estimatedRowHeight = 70;
    recycler->registerCell("Cell", []() { return RecyclerCellTest::create(); });
    recycler->setDataSource(new TestDataSource());
}

brls::View* RecyclingTest::create()
{
    // Called by the XML engine to create a new RecyclingListTab
    return new RecyclingTest();
}
