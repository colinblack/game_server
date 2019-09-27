package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class GetQQgamePrivilegeGrowAward
	{
		public static const PROTO:String = "ProtoActivityTencent.GetQQgamePrivilegeGrowAward";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function GetQQgamePrivilegeGrowAward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetQQgamePrivilegeGrowAward
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetQQgamePrivilegeGrowAward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}