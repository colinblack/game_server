package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSInviteUserResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSInviteUserResp";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var martialGrade:int;
		public var slot:int;
		public function ProtoCSInviteUserResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			martialGrade = undefined;
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.martialGrade = this.martialGrade;
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSInviteUserResp
		{
			myUid = undefined;
			martialGrade = undefined;
			slot = undefined;
			this.myUid = msgObj.myUid;
			this.martialGrade = msgObj.martialGrade;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSInviteUserResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}