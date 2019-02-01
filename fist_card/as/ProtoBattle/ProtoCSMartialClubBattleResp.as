package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSMartialClubBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoCSMartialClubBattleResp";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var mymGrade:int;
		public var othUid:int;
		public var othmGrade:int;
		public var othProtectTs:int;
		public var othCoins:int;
		public var othProps:Vector.<MartialClubProp>;
		public var hero:Vector.<HeroBaseInfoCPP>;
		public var common:BattleCommonCPP;
		public function ProtoCSMartialClubBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			mymGrade = undefined;
			othUid = undefined;
			othmGrade = undefined;
			othProtectTs = undefined;
			othCoins = undefined;
			othProps = new Vector.<MartialClubProp>();
			hero = new Vector.<HeroBaseInfoCPP>();
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.mymGrade = this.mymGrade;
			serializeObj.othUid = this.othUid;
			serializeObj.othmGrade = this.othmGrade;
			serializeObj.othProtectTs = this.othProtectTs;
			serializeObj.othCoins = this.othCoins;
			serializeObj.othProps = [];
			for(var i:int = 0;i < this.othProps.length;i++)
			{
				serializeObj.othProps.push(this.othProps[i].serialize());
			}
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			if(this.common!= undefined)
			{
				serializeObj.common = this.common.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSMartialClubBattleResp
		{
			myUid = undefined;
			mymGrade = undefined;
			othUid = undefined;
			othmGrade = undefined;
			othProtectTs = undefined;
			othCoins = undefined;
			othProps = new Vector.<MartialClubProp>();
			hero = new Vector.<HeroBaseInfoCPP>();
			common = undefined;
			this.myUid = msgObj.myUid;
			this.mymGrade = msgObj.mymGrade;
			this.othUid = msgObj.othUid;
			this.othmGrade = msgObj.othmGrade;
			this.othProtectTs = msgObj.othProtectTs;
			this.othCoins = msgObj.othCoins;
			for(var i:int = 0;i < msgObj.othProps.length;i++)
			{
				this.othProps.push(new MartialClubProp(package_root).unserialize(msgObj.othProps[i]));
			}
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero[i]));
			}
			if(msgObj.hasOwnProperty("common"))
			{
				this.common = new BattleCommonCPP(package_root).unserialize(msgObj.common);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSMartialClubBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}