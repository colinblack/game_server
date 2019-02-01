package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetInviteRewardResp
	{
		public static const PROTO:String = "User.GetInviteRewardResp";
		public var package_root:*;
		public  var message:*;
		public var mark:Number;
		public var commons:CommonItemsCPP;
		public function GetInviteRewardResp(root:*)
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
		public function unserialize(msgObj:*):GetInviteRewardResp
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
		public function decode(buffer:*):GetInviteRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}