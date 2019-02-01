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
		public var mymGrade:int;
		public var othUid:int;
		public var othmGrade:int;
		public function ProtoCSMartialClubBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			mymGrade = undefined;
			othUid = undefined;
			othmGrade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.mymGrade = this.mymGrade;
			serializeObj.othUid = this.othUid;
			serializeObj.othmGrade = this.othmGrade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSMartialClubBattleReq
		{
			myUid = undefined;
			mymGrade = undefined;
			othUid = undefined;
			othmGrade = undefined;
			this.myUid = msgObj.myUid;
			this.mymGrade = msgObj.mymGrade;
			this.othUid = msgObj.othUid;
			this.othmGrade = msgObj.othmGrade;
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