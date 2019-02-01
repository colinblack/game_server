package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSMartialClubBattleReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoCSMartialClubBattleReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var level:int;
		public var myName:String;
		public var myFig:String;
		public var myMartialGrade:int;
		public var othUid:int;
		public var othMartialGrade:int;
		public var common:BattleCommon;
		public var hero:Vector.<HeroBaseInfoCPP>;
		public function ProtoCSMartialClubBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			level = undefined;
			myName = undefined;
			myFig = undefined;
			myMartialGrade = undefined;
			othUid = undefined;
			othMartialGrade = undefined;
			common = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.level = this.level;
			serializeObj.myName = this.myName;
			serializeObj.myFig = this.myFig;
			serializeObj.myMartialGrade = this.myMartialGrade;
			serializeObj.othUid = this.othUid;
			serializeObj.othMartialGrade = this.othMartialGrade;
			serializeObj.common = this.common.serialize();
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSMartialClubBattleReq
		{
			myUid = undefined;
			level = undefined;
			myName = undefined;
			myFig = undefined;
			myMartialGrade = undefined;
			othUid = undefined;
			othMartialGrade = undefined;
			common = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
			this.myUid = msgObj.myUid;
			this.level = msgObj.level;
			this.myName = msgObj.myName;
			this.myFig = msgObj.myFig;
			this.myMartialGrade = msgObj.myMartialGrade;
			this.othUid = msgObj.othUid;
			this.othMartialGrade = msgObj.othMartialGrade;
			this.common = new BattleCommon(package_root).unserialize(msgObj.common);
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSMartialClubBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}