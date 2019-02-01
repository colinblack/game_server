package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class CommonItemsCPP
	{
		public static const PROTO:String = "DataCommon.CommonItemsCPP";
		public var package_root:*;
		public  var message:*;
		public var userbase:UserBaseChangeCPP;
		public var props:PropsAllChangeCPP;
		public function CommonItemsCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			userbase = undefined;
			props = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.userbase!= undefined)
			{
				serializeObj.userbase = this.userbase.serialize();
			}
			if(this.props!= undefined)
			{
				serializeObj.props = this.props.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CommonItemsCPP
		{
			userbase = undefined;
			props = undefined;
			if(msgObj.hasOwnProperty("userbase"))
			{
				this.userbase = new UserBaseChangeCPP(package_root).unserialize(msgObj.userbase);
			}
			if(msgObj.hasOwnProperty("props"))
			{
				this.props = new PropsAllChangeCPP(package_root).unserialize(msgObj.props);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CommonItemsCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}