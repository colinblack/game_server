package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSDelParttimerToBattleReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSDelParttimerToBattleReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var heroId:int;
		public function ProtoCSDelParttimerToBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			heroId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.heroId = this.heroId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSDelParttimerToBattleReq
		{
			myUid = undefined;
			heroId = undefined;
			this.myUid = msgObj.myUid;
			this.heroId = msgObj.heroId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSDelParttimerToBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}