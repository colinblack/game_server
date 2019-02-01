package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetInviteRewardReq
	{
		public static const PROTO:String = "User.GetInviteRewardReq";
		public var package_root:*;
		public  var message:*;
		public var seq:int;
		public function GetInviteRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			seq = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.seq = this.seq;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetInviteRewardReq
		{
			seq = undefined;
			this.seq = msgObj.seq;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetInviteRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}