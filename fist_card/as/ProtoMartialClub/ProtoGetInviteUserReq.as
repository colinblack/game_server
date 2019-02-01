package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetInviteUserReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetInviteUserReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoGetInviteUserReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetInviteUserReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetInviteUserReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}