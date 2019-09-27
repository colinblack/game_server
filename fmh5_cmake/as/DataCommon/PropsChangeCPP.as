package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import laya.utils.Byte;
	public class PropsChangeCPP
	{
		public static const PROTO:String = "DataCommon.PropsChangeCPP";
		public var package_root:*;
		public  var message:*;
		public var change:int;
		public var props:PropsItemCPP;
		public function PropsChangeCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			change = undefined;
			props = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.change = this.change;
			serializeObj.props = this.props.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PropsChangeCPP
		{
			change = undefined;
			props = undefined;
			this.change = msgObj.change;
			this.props = new PropsItemCPP(package_root).unserialize(msgObj.props);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PropsChangeCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}