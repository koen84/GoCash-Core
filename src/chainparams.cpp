// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The GoCash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "bignum.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000c3e7814dac5cc0e41b2049dbed4b50809cca911c0e216639ce4e9d46823"))
    (47274, uint256("0xf4d0e3e70e368d8f31fadab004578da2889d2d526cb27224c789d7a389a5a83e"))
    (128982, uint256("0x0b23d9e3c7aff21ef5d61afd2ed7daab0378274a886cb2ca4a40b02db75dccdc"))
    (182663, uint256("0x93eb2dc632d831a121983ccbcd70118b5fbed24fded0d54902af6f7c45eae6d5"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1528115717, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1200        // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000087f29a39a18416054d6c83842cabc5c21313d82c72877d3c3f0f9521de0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0e05e5d9a61a7160a545b16647b85bcb138b4bd9737c8f8de76b0c9f61044d4c"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x24;
        pchMessageStart[1] = 0x25;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("04ffff001d01043f4743415348206973206f7572732c20576520666f756e642069742066697273742c2047434153482077696c6c20616c7761797320666f7220476f2043617368");
        nDefaultPort = 17121;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 100;
        nMaturity = 30;
        nMasternodeCountDrift = 20;
	    nMasternodeColleteralLimxDev = 10000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 5000000 * COIN;

        const char* pszTimestamp = "GCASH is ours, We found it first, GCASH will always for Go Cash";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime =1540031822;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1910714;

        /*
        python gen.py -a quark -t 1540031822 -z "GCASH is ours, We found it first, GCASH will always for Go Cash" -p "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"
04ffff001d01043f4743415348206973206f7572732c20576520666f756e642069742066697273742c2047434153482077696c6c20616c7761797320666f7220476f2043617368
algorithm: quark
merkle hash: 582b56d0675f8b4cf0fce01f478cce0e9cec9332a2872d6cc05c759202801625
pszTimestamp: GCASH is ours, We found it first, GCASH will always for Go Cash
pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
time: 1540031822
bits: 0x1e0ffff0
Searching for genesis hash...
genesis hash found!
nonce: 1910714
genesis hash: 00000b1a5a099291be2a4c5fabd507f8d808210bc5455975109111246384a9b8
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000b1a5a099291be2a4c5fabd507f8d808210bc5455975109111246384a9b8"));
        assert(genesis.hashMerkleRoot == uint256("0x582b56d0675f8b4cf0fce01f478cce0e9cec9332a2872d6cc05c759202801625"));


        vSeeds.push_back(CDNSSeedData("0", "168.235.85.91:17121"));
        vSeeds.push_back(CDNSSeedData("1", "149.28.169.115:17121"));
        vSeeds.push_back(CDNSSeedData("2", "73.255.148.181:17121"));
        vSeeds.push_back(CDNSSeedData("3", "83.79.38.57:17121"));
        vSeeds.push_back(CDNSSeedData("4", "101.180.5.119:17121"));
        vSeeds.push_back(CDNSSeedData("5", "118.38.99.125:17121"));
        vSeeds.push_back(CDNSSeedData("6", "207.148.9.75:17121"));
        vSeeds.push_back(CDNSSeedData("7", "76.169.4.118:17121"));
        vSeeds.push_back(CDNSSeedData("8", "149.28.126.31:17121"));
        vSeeds.push_back(CDNSSeedData("9", "122.169.8.234:17121"));
        vSeeds.push_back(CDNSSeedData("10", "23.94.136.165:17121"));
        vSeeds.push_back(CDNSSeedData("11", "36.74.153.225:17121"));
        vSeeds.push_back(CDNSSeedData("12", "112.215.172.80:17121"));
        vSeeds.push_back(CDNSSeedData("13", "45.76.61.220:17121"));
        vSeeds.push_back(CDNSSeedData("14", "47.254.33.204:17121"));
        vSeeds.push_back(CDNSSeedData("15", "165.73.50.200:17121"));
        vSeeds.push_back(CDNSSeedData("16", "36.69.131.37:17121"));
        vSeeds.push_back(CDNSSeedData("17", "144.202.61.134:17121"));
        vSeeds.push_back(CDNSSeedData("18", "192.227.215.169:17121"));
        vSeeds.push_back(CDNSSeedData("19", "98.214.20.153:17121"));
        vSeeds.push_back(CDNSSeedData("20", "201.53.46.148:17121"));
        vSeeds.push_back(CDNSSeedData("21", "173.48.82.37:17121"));
        vSeeds.push_back(CDNSSeedData("22", "90.254.158.239:17121"));
        vSeeds.push_back(CDNSSeedData("23", "178.120.10.82:17121"));
        vSeeds.push_back(CDNSSeedData("24", "180.191.74.218:17121"));
        vSeeds.push_back(CDNSSeedData("25", "36.70.206.23:17121"));
        vSeeds.push_back(CDNSSeedData("26", "122.173.15.75:17121"));
        vSeeds.push_back(CDNSSeedData("27", "151.106.19.121:17121"));
        vSeeds.push_back(CDNSSeedData("28", "183.81.155.6:17121"));
        vSeeds.push_back(CDNSSeedData("29", "173.90.87.168:17121"));
        vSeeds.push_back(CDNSSeedData("30", "45.76.251.234:17121"));
        vSeeds.push_back(CDNSSeedData("31", "46.33.239.29:17121"));
        vSeeds.push_back(CDNSSeedData("32", "36.80.67.175:17121"));
        vSeeds.push_back(CDNSSeedData("33", "180.243.188.73:17121"));
        vSeeds.push_back(CDNSSeedData("34", "168.195.101.48:17121"));
        vSeeds.push_back(CDNSSeedData("35", "221.37.194.27:17121"));
        vSeeds.push_back(CDNSSeedData("36", "115.178.211.116:17121"));
        vSeeds.push_back(CDNSSeedData("37", "99.95.101.88:17121"));
        vSeeds.push_back(CDNSSeedData("38", "99.59.239.8:17121"));
        vSeeds.push_back(CDNSSeedData("39", "112.215.153.161:17121"));
        vSeeds.push_back(CDNSSeedData("39", "168.235.85.91:17121"));
        vSeeds.push_back(CDNSSeedData("40", "185.52.3.182:17121"));
        vSeeds.push_back(CDNSSeedData("41", "149.28.140.123:17121"));
        vSeeds.push_back(CDNSSeedData("42", "183.81.155.6:17121"));
        vSeeds.push_back(CDNSSeedData("43", "168.235.65.99:17121"));
        //vFixedSeeds.clear();
        //vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 102);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;


        nPoolMaxTransactions = 3;
        strSporkKey = "0478c3e932fbe183b2f665de937866cb1cfc5ed4b0bf733b72286f265ffc03ff52dfd669fbb3f77d630e5393da65c721a9a891d2c4c6aa515dfd25ffe545582357";
        strDarksendPoolDummyAddress = "AcmpqXViWUXNroqVNYRdKjKrFM6PNa1oTM";
        nStartMasternodePayments = 1540031822; 
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        vAlertPubKey = ParseHex("0485286086a0871308bf36519edb18d95bbe9b098abe14ec9b684b5255028ec644bacdbddb98a522a6bcd7ab8e7d3582d7a5b9bf59c427f7eabce447b5ba6de25f");
        nDefaultPort = 56123;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 30 Apr 2018 04:00:00 GMT
        nMaxMoneyOut = 90000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1523116994;
        genesis.nNonce = 21734390;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000087f29a39a18416054d6c83842cabc5c21313d82c72877d3c3f0f9521de0"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 12);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 34);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 173);
        // Testnet GoCash BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet GoCash BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet GoCash BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 2;
        strSporkKey = "04363509d5c65f5a9ca7ceedad4887007ae85469d249a6f566b788504ee5e105bcf1bbc515f49a7aac3bceb8864bb2ba84bebd92c66ff9022309e2bfbd5f70d11f";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1523116994;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 1 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1523116995;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 5;
		nDefaultPort = 57123;

        hashGenesisBlock = genesis.GetHash();
     
        assert(hashGenesisBlock == uint256("0x0e05e5d9a61a7160a545b16647b85bcb138b4bd9737c8f8de76b0c9f61044d4c"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 56123;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
