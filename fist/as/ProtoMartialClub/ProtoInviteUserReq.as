package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoInviteUserReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoInviteUserReq";
		public var package_root:*;
		public  var message:*;
		public var othUid:int;
		public var martialGrade:int;
		public function ProtoInviteUserReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			othUid = undefined;
			martialGrade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othUid = this.othUid;
			serializeObj.martialGrade = this.martialGrade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoInviteUserReq
		{
			othUid = undefined;
			martialGrade = undefined;
			this.othUid = msgObj.othUid;
			this.martialGrade = msgObj.martialGrade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoInviteUserReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}