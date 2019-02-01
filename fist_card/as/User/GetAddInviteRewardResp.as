package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetAddInviteRewardResp
	{
		public static const PROTO:String = "User.GetAddInviteRewardResp";
		public var package_root:*;
		public  var message:*;
		public var mark:int;
		public var commons:CommonItemsCPP;
		public function GetAddInviteRewardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			mark = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.mark = this.mark;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetAddInviteRewardResp
		{
			mark = undefined;
			commons = undefined;
			this.mark = msgObj.mark;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetAddInviteRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}