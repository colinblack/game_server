package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetAddInviteRewardReq
	{
		public static const PROTO:String = "User.GetAddInviteRewardReq";
		public var package_root:*;
		public  var message:*;
		public var num:int;
		public function GetAddInviteRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			num = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.num = this.num;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetAddInviteRewardReq
		{
			num = undefined;
			this.num = msgObj.num;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetAddInviteRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}