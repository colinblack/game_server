package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class ConcernFolkCPP
	{
		public static const PROTO:String = "ProtoFriend.ConcernFolkCPP";
		public var package_root:*;
		public  var message:*;
		public var concernfolk:FolkCPP;
		public function ConcernFolkCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			concernfolk = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.concernfolk = this.concernfolk.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ConcernFolkCPP
		{
			concernfolk = undefined;
			this.concernfolk = new FolkCPP(package_root).unserialize(msgObj.concernfolk);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ConcernFolkCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}