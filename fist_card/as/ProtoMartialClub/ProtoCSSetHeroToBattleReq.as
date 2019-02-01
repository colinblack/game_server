package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSSetHeroToBattleReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSSetHeroToBattleReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var othUid:int;
		public var heroId:int;
		public var slot:int;
		public var level:int;
		public var heroNum:int;
		public function ProtoCSSetHeroToBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
			level = undefined;
			heroNum = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.othUid = this.othUid;
			serializeObj.heroId = this.heroId;
			serializeObj.slot = this.slot;
			serializeObj.level = this.level;
			serializeObj.heroNum = this.heroNum;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSSetHeroToBattleReq
		{
			myUid = undefined;
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
			level = undefined;
			heroNum = undefined;
			this.myUid = msgObj.myUid;
			this.othUid = msgObj.othUid;
			this.heroId = msgObj.heroId;
			this.slot = msgObj.slot;
			this.level = msgObj.level;
			this.heroNum = msgObj.heroNum;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSSetHeroToBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}