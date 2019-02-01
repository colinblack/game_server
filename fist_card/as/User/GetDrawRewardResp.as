package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetDrawRewardResp
	{
		public static const PROTO:String = "User.GetDrawRewardResp";
		public var package_root:*;
		public  var message:*;
		public var nextId:int;
		public var index:int;
		public var commons:CommonItemsCPP;
		public function GetDrawRewardResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			nextId = undefined;
			index = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextId = this.nextId;
			serializeObj.index = this.index;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetDrawRewardResp
		{
			nextId = undefined;
			index = undefined;
			commons = undefined;
			this.nextId = msgObj.nextId;
			this.index = msgObj.index;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetDrawRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}